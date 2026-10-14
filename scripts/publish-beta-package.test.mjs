import assert from 'node:assert/strict';
import { execFileSync } from 'node:child_process';
import { mkdtempSync, mkdirSync, readFileSync, rmSync, writeFileSync } from 'node:fs';
import { tmpdir } from 'node:os';
import path from 'node:path';
import { test } from 'node:test';
import { fileURLToPath } from 'node:url';
import { nextBetaVersion, publishBetaPackage } from './publish-beta-package.mjs';

test('a new PR starts at revision one and later publishes increment that PR', () => {
    assert.equal(nextBetaVersion('1.2.6', 430, []), '1.2.6-beta.430.1');
    assert.equal(nextBetaVersion('1.2.6', 430, ['1.2.6-beta.430.1']), '1.2.6-beta.430.2');
    assert.equal(nextBetaVersion('1.2.6', 430, ['1.2.6-beta.430.2', '1.2.6-beta.430.10']),
        '1.2.6-beta.430.11');
});

test('other PRs, base versions, channels and old run-based versions do not set the PR revision', () => {
    const versions = ['1.2.6-beta.429.99', '1.2.5-beta.430.99', '1.2.6-rc.430.99',
        '1.2.6-beta.374.1', '1.2.6-beta.4300.5', '1.2.6-beta.430.1.extra'];
    assert.equal(nextBetaVersion('1.2.6', 430, versions), '1.2.6-beta.430.1');
    assert.equal(nextBetaVersion('1.2.7', 430, ['1.2.6-beta.430.3']), '1.2.7-beta.430.1');
});

test('invalid release inputs fail rather than inventing a package version', () => {
    for (const pr of [0, -1, NaN, 1.5]) assert.throws(() => nextBetaVersion('1.2.6', pr, []));
    assert.throws(() => nextBetaVersion('1.2.6-beta.430.1', 430, []));
    assert.throws(() => nextBetaVersion('1.2.6', 430, {}));
    assert.throws(() => nextBetaVersion('1.2.6', 430, [42]));
    assert.throws(() => nextBetaVersion('1.2.6', 430, ['1.2.6-beta.430.9007199254740991']));
});

const packageData = { name: 'measur-tools-suite', baseVersion: '1.2.6', prNumber: 430 };

test('publishes the next PR revision and reports the exact successful version', () => {
    const calls = [];
    const result = publishBetaPackage(packageData, args => {
        calls.push(args);
        if (args[0] === 'view') return '["1.2.6-beta.430.1"]';
        return '';
    });
    assert.equal(result, '1.2.6-beta.430.2');
    assert.deepEqual(calls, [
        ['view', 'measur-tools-suite', 'versions', '--json', '--prefer-online'],
        ['--no-git-tag-version', 'version', '1.2.6-beta.430.2'],
        ['publish', '--tag', 'beta'],
    ]);
});

test('a confirmed collision advances even while the registry version list is stale', () => {
    const assigned = [];
    let publishes = 0;
    const result = publishBetaPackage(packageData, args => {
        if (args[0] === 'view' && args[2] === 'versions') return '[]';
        if (args[0] === 'view') return '"1.2.6-beta.430.1"';
        if (args[0] === '--no-git-tag-version') assigned.push(args[2]);
        if (args[0] === 'publish' && ++publishes === 1) throw new Error('occupied version');
        return '';
    });
    assert.equal(result, '1.2.6-beta.430.2');
    assert.deepEqual(assigned, ['1.2.6-beta.430.1', '1.2.6-beta.430.2']);
});

test('registry outages and malformed version responses cannot trigger publication', () => {
    const offline = new Error('registry offline');
    assert.throws(() => publishBetaPackage(packageData, () => { throw offline; }), error => error === offline);
    assert.throws(() => publishBetaPackage(packageData, () => 'invalid JSON'), SyntaxError);
});

test('unconfirmed authentication or network publication errors fail without retrying', () => {
    const failure = new Error('unauthorized');
    let publishes = 0;
    assert.throws(() => publishBetaPackage(packageData, args => {
        if (args[0] === 'view' && args[2] === 'versions') return '[]';
        if (args[0] === 'view') throw new Error('version does not exist');
        if (args[0] === 'publish') { ++publishes; throw failure; }
        return '';
    }), error => error === failure);
    assert.equal(publishes, 1);
});

test('persistent confirmed collisions stop after five attempts', () => {
    let publishes = 0;
    assert.throws(() => publishBetaPackage(packageData, args => {
        if (args[0] === 'view' && args[2] === 'versions') return '[]';
        if (args[0] === 'view') return JSON.stringify(args[1].slice(args[1].indexOf('@') + 1));
        if (args[0] === 'publish') { ++publishes; throw new Error('occupied version'); }
        return '';
    }), /after five attempts/);
    assert.equal(publishes, 5);
});

test('the workflow entrypoint writes the exact output only after successful publication', () => {
    const directory = mkdtempSync(path.join(tmpdir(), 'measur-beta-test-'));
    try {
        const bin = path.join(directory, 'bin');
        mkdirSync(bin);
        writeFileSync(path.join(directory, 'package.json'), JSON.stringify({
            name: 'measur-tools-suite', version: '1.2.6',
        }));
        // An isolated npm fixture exercises the actual CLI without accessing a registry or publishing.
        writeFileSync(path.join(bin, 'npm'), `#!/usr/bin/env node
const args = process.argv.slice(2);
if (args[0] === 'view' && args[2] === 'versions') {
    process.stdout.write('["1.2.6-beta.430.1"]');
} else if (args[0] === 'view' || (args[0] === 'publish' && process.env.FAKE_PUBLISH_FAILURE)) {
    process.exit(1);
}
`, { mode: 0o755 });
        const output = path.join(directory, 'output');
        writeFileSync(output, '');
        const env = { ...process.env, PATH: `${bin}${path.delimiter}${process.env.PATH}`,
            PR_NUMBER: '430', GITHUB_OUTPUT: output };
        delete env.FAKE_PUBLISH_FAILURE;
        const script = fileURLToPath(new URL('./publish-beta-package.mjs', import.meta.url));
        execFileSync(process.execPath, [script], { cwd: directory, env, stdio: 'pipe' });
        assert.equal(readFileSync(output, 'utf8'), 'PKG_VERSION=1.2.6-beta.430.2\n');
        writeFileSync(output, '');
        assert.throws(() => execFileSync(process.execPath, [script], {
            cwd: directory, env: { ...env, FAKE_PUBLISH_FAILURE: '1' }, stdio: 'pipe',
        }));
        assert.equal(readFileSync(output, 'utf8'), '');
    } finally {
        rmSync(directory, { recursive: true, force: true });
    }
});
