import { execFileSync } from 'node:child_process';
import { appendFileSync, readFileSync } from 'node:fs';
import { pathToFileURL } from 'node:url';

/** Choose the next published revision for one exact base version and PR. */
export function nextBetaVersion(baseVersion, prNumber, publishedVersions, minimumRevision = 1) {
    if (!/^\d+\.\d+\.\d+$/.test(baseVersion)) throw new Error('Expected a stable base package version');
    if (!Number.isSafeInteger(prNumber) || prNumber < 1) throw new Error('Expected a positive PR number');
    if (!Array.isArray(publishedVersions) || publishedVersions.some(version => typeof version !== 'string')) {
        throw new Error('Expected an array of published version strings');
    }
    if (!Number.isSafeInteger(minimumRevision) || minimumRevision < 1) {
        throw new Error('Expected a positive minimum revision');
    }

    const prefix = `${baseVersion}-beta.${prNumber}.`;
    let revision = minimumRevision;
    for (const version of publishedVersions) {
        if (!version.startsWith(prefix)) continue;
        const suffix = version.slice(prefix.length);
        if (!/^[1-9]\d*$/.test(suffix)) continue;
        const published = Number(suffix);
        if (!Number.isSafeInteger(published) || published === Number.MAX_SAFE_INTEGER) {
            throw new Error('Published beta revision exceeds the supported range');
        }
        revision = Math.max(revision, published + 1);
    }
    return `${prefix}${revision}`;
}

function runNpm(args) {
    return execFileSync('npm', args, {
        encoding: 'utf8',
        stdio: ['ignore', 'pipe', 'pipe'],
        timeout: 120_000,
    });
}

/**
 * Publish under the serialized beta release job. Never mask registry failures as an empty index.
 * If a stale index selects an occupied version, confirm that exact version exists before retrying.
 */
export function publishBetaPackage({ name, baseVersion, prNumber }, npm = runNpm) {
    let minimumRevision = 1;
    for (let attempt = 0; attempt < 5; ++attempt) {
        const versions = JSON.parse(npm(['view', name, 'versions', '--json', '--prefer-online']));
        const version = nextBetaVersion(baseVersion, prNumber, versions, minimumRevision);
        npm(['--no-git-tag-version', 'version', version]);
        try {
            npm(['publish', '--tag', 'beta']);
            return version;
        } catch (publishError) {
            // Authorization, network and other publication failures must fail the job.
            // Retry only a confirmed occupied version, not an arbitrary npm error.
            let existing;
            try {
                existing = JSON.parse(npm(['view', `${name}@${version}`, 'version', '--json', '--prefer-online']));
            } catch {
                throw publishError;
            }
            if (existing !== version) throw publishError;
            minimumRevision = Number(version.slice(version.lastIndexOf('.') + 1)) + 1;
            console.error(`Version ${version} already exists; retrying the next PR revision.`);
        }
    }
    throw new Error('Could not allocate an unpublished beta version after five attempts');
}

if (process.argv[1] && import.meta.url === pathToFileURL(process.argv[1]).href) {
    if (!process.env.GITHUB_OUTPUT) throw new Error('GITHUB_OUTPUT is required for the release workflow');
    const manifest = JSON.parse(readFileSync('package.json', 'utf8'));
    const version = publishBetaPackage({
        name: manifest.name,
        baseVersion: manifest.version,
        prNumber: Number(process.env.PR_NUMBER),
    });
    appendFileSync(process.env.GITHUB_OUTPUT, `PKG_VERSION=${version}\n`);
    console.log(`Published ${manifest.name}@${version}`);
}
