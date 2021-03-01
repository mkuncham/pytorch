#include <torch/csrc/jit/api/module.h>
#include <torch/csrc/jit/serialization/export.h>

namespace torch {
namespace jit {

void Module::save(std::ostream& out, const ExtraFilesMap& extra_files) const {
  ExportModule(*this, out, extra_files, false /* bytecode_format */);
}

void Module::save(const std::string& filename, const ExtraFilesMap& extra_files)
    const {
  ExportModule(*this, filename, extra_files, false /* bytecode_format */);
}

void Module::_save_for_mobile(
    std::ostream& out,
    const ExtraFilesMap& extra_files,
    bool save_mobile_debug_info) const {
  auto cloned_module = this->clone();
  if (!cloned_module.hasattr("is_mobile_module")) {
    cloned_module.register_attribute("is_mobile_module", BoolType::get(), true);
  }

  ExportModule(
      cloned_module,
      out,
      extra_files,
      true /* bytecode_format */,
      save_mobile_debug_info);
}

void Module::_save_for_mobile(
    const std::string& filename,
    const ExtraFilesMap& extra_files,
    bool save_mobile_debug_info) const {
  auto cloned_module = this->clone();
  if (!cloned_module.hasattr("is_mobile_module")) {
    cloned_module.register_attribute("is_mobile_module", BoolType::get(), true);
  }
  ExportModule(
      cloned_module,
      filename,
      extra_files,
      true /* bytecode_format */,
      save_mobile_debug_info);
}

} // namespace jit
} // namespace torch
