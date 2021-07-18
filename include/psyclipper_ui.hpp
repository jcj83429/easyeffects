/*
 *  Copyright © 2017-2021 Wellington Wallace, Jason Jang
 *
 *  This file is part of EasyEffects.
 *
 *  EasyEffects is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  EasyEffects is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with EasyEffects.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef PSYCLIPPER_UI_HPP
#define PSYCLIPPER_UI_HPP

#include "plugin_ui_base.hpp"

class PsyClipperUi : public Gtk::Box, public PluginUiBase {
 public:
  PsyClipperUi(BaseObjectType* cobject,
            const Glib::RefPtr<Gtk::Builder>& builder,
            const std::string& schema,
            const std::string& schema_path);
  PsyClipperUi(const PsyClipperUi&) = delete;
  auto operator=(const PsyClipperUi&) -> PsyClipperUi& = delete;
  PsyClipperUi(const PsyClipperUi&&) = delete;
  auto operator=(const PsyClipperUi&&) -> PsyClipperUi& = delete;
  ~PsyClipperUi() override;

  static auto add_to_stack(Gtk::Stack* stack, const std::string& schema_path) -> PsyClipperUi*;

  void on_new_protection_reduction(double value);

  void reset() override;

 private:
  Gtk::SpinButton *clip_level = nullptr, *iterations = nullptr,
                  *adaptive_distortion = nullptr;

  Gtk::Scale *input_gain = nullptr, *output_gain = nullptr,
             *protection125 = nullptr, *protection250 = nullptr, *protection500 = nullptr, *protection1000 = nullptr,
             *protection2000 = nullptr, *protection4000 = nullptr, *protection8000 = nullptr, *protection16000 = nullptr;

  Gtk::ToggleButton *auto_level = nullptr, *diff_only = nullptr;

  Gtk::LevelBar* protection_reduction = nullptr;

  Gtk::Label* protection_reduction_label = nullptr;
};

#endif
