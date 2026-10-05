import fs from 'node:fs';
import path from 'node:path';
import { fileURLToPath } from 'node:url';

const scriptDirectory = path.dirname(fileURLToPath(import.meta.url));
const repositoryRoot = path.resolve(scriptDirectory, '..');
const ignoredDirectories = new Set([
    '.git',
    'build',
    'build-cpp',
    'build-wasm',
    'docs/html',
    'node_modules'
]);

function isIgnored(candidatePath) {
    const relativePath = path.relative(repositoryRoot, candidatePath);
    return [...ignoredDirectories].some((entry) =>
        relativePath === entry || relativePath.startsWith(`${entry}${path.sep}`)
    );
}

function collectMarkdownFiles(directory, files = []) {
    for (const entry of fs.readdirSync(directory, { withFileTypes: true })) {
        const entryPath = path.join(directory, entry.name);
        if (isIgnored(entryPath)) {
            continue;
        }
        if (entry.isDirectory()) {
            collectMarkdownFiles(entryPath, files);
        } else if (entry.isFile() && entry.name.endsWith('.md')) {
            files.push(entryPath);
        }
    }
    return files;
}

function normalizeTarget(rawTarget) {
    let target = rawTarget.trim();
    if (target.startsWith('<') && target.endsWith('>')) {
        target = target.slice(1, -1);
    } else {
        target = target.replace(/\s+["'][^"']*["']$/, '');
    }
    return target.split('#', 1)[0].split('?', 1)[0];
}

const missingLinks = [];
const markdownLink = /!?\[[^\]]*\]\(([^)]+)\)/g;

for (const markdownPath of collectMarkdownFiles(repositoryRoot)) {
    const contents = fs.readFileSync(markdownPath, 'utf8');
    for (const match of contents.matchAll(markdownLink)) {
        const rawTarget = match[1].trim();
        if (/^(?:[a-z]+:|#)/i.test(rawTarget)) {
            continue;
        }

        const normalizedTarget = normalizeTarget(rawTarget);
        if (!normalizedTarget) {
            continue;
        }

        let decodedTarget;
        try {
            decodedTarget = decodeURIComponent(normalizedTarget);
        } catch {
            decodedTarget = normalizedTarget;
        }

        const resolvedTarget = decodedTarget.startsWith('/')
            ? path.join(repositoryRoot, decodedTarget)
            : path.resolve(path.dirname(markdownPath), decodedTarget);

        if (!fs.existsSync(resolvedTarget)) {
            missingLinks.push({
                file: path.relative(repositoryRoot, markdownPath),
                target: rawTarget
            });
        }
    }
}

if (missingLinks.length > 0) {
    console.error('Missing local Markdown targets:');
    for (const missingLink of missingLinks) {
        console.error(`- ${missingLink.file}: ${missingLink.target}`);
    }
    process.exit(1);
}

console.log('All local Markdown link targets exist.');
