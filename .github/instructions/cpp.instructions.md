---
applyTo: "{include,src,tests/cpp}/**/*.{h,cpp}"
---

# C++ Review Focus

- Compare public declarations, definitions, namespaces, parameter order, defaults, and focused tests.
- Treat formulas, constants, units, sentinels, and boundary behavior as calculation contracts; require evidence for intentional changes.
- Check public Doxygen comments for meaning and units without requesting implementation narration.
- Flag behavior changes that lack explicit approval, golden before/after results, or corresponding tests.
