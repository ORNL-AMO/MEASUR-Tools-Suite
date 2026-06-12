#!/usr/bin/env python3
"""
Convert commented-out std::cout debug logging in steamModeler .cpp files to SM_LOG() calls.

For each file:
  1. Adds #include "steamModeler/util/SteamModelerLogger.h" after the first #include block.
  2. Finds all `// std::cout << ...` blocks (single or multi-line) and replaces them with
     SM_LOG(...) calls.

Multi-line blocks are those where the first line does not end with `<< std::endl;`.
Subsequent comment lines are collected until `std::endl;` is found.
"""

import re
import sys
import os

LOGGER_INCLUDE = '#include "steamModeler/util/SteamModelerLogger.h"\n'
LOGGER_GUARD   = 'steamModeler/util/SteamModelerLogger.h'

# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

def _remove_endl(s: str) -> str:
    """Strip the trailing `<< std::endl;` (and anything after) from an expression."""
    return re.sub(r'\s*<<\s*std::endl\s*;.*$', '', s).strip()


def _strip_comment_prefix(line: str) -> str:
    """Remove leading whitespace and // from a comment line, return the rest."""
    return re.sub(r'^\s*//', '', line).strip()


def transform_cout_blocks(lines: list[str]) -> list[str]:
    """
    Walk through lines and convert `// std::cout << ...` comment blocks to SM_LOG calls.
    The indentation of the original comment is preserved.
    """
    result: list[str] = []
    i = 0

    while i < len(lines):
        line = lines[i]

        # Detect start of a commented cout block.
        # Matches:  // std::cout <<  or  //  std::cout <<  (extra leading spaces inside //)
        m = re.match(r'^(\s*)//\s*std::cout\s*<<\s*(.*)', line)
        if m:
            indent       = m.group(1)
            first_content = m.group(2).rstrip()

            # ---- Single-line case ----------------------------------------
            if 'std::endl' in first_content:
                expr = _remove_endl(first_content)
                result.append(f'{indent}SM_LOG({expr});\n')
                i += 1
                continue

            # ---- Multi-line case -----------------------------------------
            # Collect continuation comment lines until we hit one with std::endl.
            content_parts = [first_content]
            j = i + 1
            found_endl = False

            while j < len(lines) and (j - i) <= 20:  # guard against run-away
                next_line = lines[j]
                # A continuation must be a comment line.
                if not re.match(r'^\s*//', next_line):
                    break
                cont = _strip_comment_prefix(next_line)
                content_parts.append(cont)
                j += 1
                if 'std::endl' in next_line:
                    found_endl = True
                    break

            if found_endl:
                merged = ' '.join(content_parts)
                expr   = _remove_endl(merged)
                result.append(f'{indent}SM_LOG({expr});\n')
                i = j
            else:
                # Could not cleanly parse — emit as-is (safety fallback).
                result.append(line)
                i += 1
            continue

        result.append(line)
        i += 1

    return result


def add_logger_include(lines: list[str]) -> list[str]:
    """
    Insert the logger include after the last consecutive #include line at the
    top of the file.  If the header is already present, do nothing.
    """
    if any(LOGGER_GUARD in ln for ln in lines):
        return lines  # already included

    # Find the last #include in the opening include block (before any non-include,
    # non-blank line that isn't a comment).
    last_include_idx = -1
    for idx, ln in enumerate(lines):
        stripped = ln.strip()
        if stripped.startswith('#include'):
            last_include_idx = idx

    insert_at = (last_include_idx + 1) if last_include_idx >= 0 else 0
    lines.insert(insert_at, LOGGER_INCLUDE)
    return lines


def process_file(filepath: str) -> bool:
    with open(filepath, 'r', encoding='utf-8') as fh:
        lines = fh.readlines()

    has_commented_cout = any(re.search(r'//\s*std::cout', ln) for ln in lines)
    if not has_commented_cout:
        return False

    new_lines = transform_cout_blocks(lines)
    new_lines = add_logger_include(new_lines)

    with open(filepath, 'w', encoding='utf-8') as fh:
        fh.writelines(new_lines)
    return True


# ---------------------------------------------------------------------------
# Entry point
# ---------------------------------------------------------------------------

if __name__ == '__main__':
    targets = sys.argv[1:]
    if not targets:
        print('Usage: convert_steam_logging.py <file1.cpp> [file2.cpp ...]')
        sys.exit(1)

    changed = 0
    for path in targets:
        if not os.path.isfile(path):
            print(f'SKIP (not found): {path}')
            continue
        if process_file(path):
            print(f'OK : {path}')
            changed += 1
        else:
            print(f'--  (no commented couts): {path}')

    print(f'\nDone. {changed}/{len(targets)} file(s) modified.')
