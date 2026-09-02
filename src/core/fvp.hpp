#pragma once

#include "formats/save_information.hpp"
#include "engine/syscall_entry.hpp"
#include "util/file/mapped_file.hpp"
#include "render_window.hpp"

#include <cstdint>
#include <memory>
#include <string_view>

namespace fvp
{

namespace Core
{

class FVP
{
public:
  void Run();

private:
  std::string_view save_file_directory_;
  std::string_view data_directory_;
  std::unique_ptr<Utility::MappedFile> overall_save_file_{nullptr};
  std::unique_ptr<Utility::MappedFile> hcb_file_{nullptr};;
  std::unique_ptr<RenderWindow> rendering_window_{nullptr};
  std::array<Formats::SaveInformation, 999> save_data_array_;
  std::vector<SyscallEntry> syscall_table_;
  std::vector<std::byte> game_title_;
  uint32_t hcb_current_file_position_{};
  uint32_t save_preview_width_{};
  uint32_t save_preview_height_{};
  uint32_t preview_save_image_width_{};
  uint32_t preview_save_image_height_{};
  uint16_t window_height_{};
  uint16_t window_width_{};
  uint16_t opcode_count_{};
  uint16_t opcodes_processed_{};

  void OpenOverallSave();
  void OpenHCBFile();
  void GetSaveInformation(uint32_t save_number);
  void InitializeData(); 

public:
  FVP();
};
} // namespace Core
} // namespace fvp
