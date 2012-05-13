#pragma once

#include <llvm/ADT/OwningPtr.h>

namespace llvm {
	class DebugLoc;
	class LLVMContext;
	class Twine;
	class raw_ostream;
} // namespace llvm

enum DiagnosticClass {
	DIAG_BUG,
	DIAG_OK,
};

class DiagnosticImpl {
public:
	virtual ~DiagnosticImpl() {}
	virtual void emit(const llvm::DebugLoc &) = 0;
	virtual void emit(const llvm::Twine &) = 0;
	virtual llvm::raw_ostream &os() = 0;
};

class Diagnostic {
public:
	Diagnostic(llvm::LLVMContext &);
	Diagnostic &operator <<(const llvm::DebugLoc &DbgLoc) {
		Diag->emit(DbgLoc);
		return *this;
	}
	Diagnostic &operator <<(const llvm::Twine &Msg) {
		Diag->emit(Msg);
		return *this;
	}
	llvm::raw_ostream &os() { return Diag->os(); }
private:
	llvm::OwningPtr<DiagnosticImpl> Diag;
};