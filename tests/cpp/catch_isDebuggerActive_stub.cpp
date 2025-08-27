// Stub for Catch::isDebuggerActive for Apple Silicon/arm64
// Place in test build to resolve linker error with old Catch2
namespace Catch {
bool isDebuggerActive() { return false; }
}
