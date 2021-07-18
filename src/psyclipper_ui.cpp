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

#include "psyclipper_ui.hpp"

PsyClipperUi::PsyClipperUi(BaseObjectType* cobject,
                     const Glib::RefPtr<Gtk::Builder>& builder,
                     const std::string& schema,
                     const std::string& schema_path)
    : Gtk::Box(cobject), PluginUiBase(builder, schema, schema_path) {
  name = plugin_name::psyclipper;

  // loading builder widgets

  auto_level = builder->get_widget<Gtk::ToggleButton>("auto_level");
  diff_only = builder->get_widget<Gtk::ToggleButton>("diff_only");
  input_gain = builder->get_widget<Gtk::Scale>("input_gain");
  output_gain = builder->get_widget<Gtk::Scale>("output_gain");
  adaptive_distortion = builder->get_widget<Gtk::SpinButton>("adaptive_distortion");
  clip_level = builder->get_widget<Gtk::SpinButton>("clip_level");
  iterations = builder->get_widget<Gtk::SpinButton>("iterations");
  protection_reduction = builder->get_widget<Gtk::LevelBar>("protection_reduction");
  protection_reduction_label = builder->get_widget<Gtk::Label>("protection_reduction_label");
  protection125 = builder->get_widget<Gtk::Scale>("protection125");
  protection250 = builder->get_widget<Gtk::Scale>("protection250");
  protection500 = builder->get_widget<Gtk::Scale>("protection500");
  protection1000 = builder->get_widget<Gtk::Scale>("protection1000");
  protection2000 = builder->get_widget<Gtk::Scale>("protection2000");
  protection4000 = builder->get_widget<Gtk::Scale>("protection4000");
  protection8000 = builder->get_widget<Gtk::Scale>("protection8000");
  protection16000 = builder->get_widget<Gtk::Scale>("protection16000");

  // gsettings bindings

  settings->bind("input-gain", input_gain->get_adjustment().get(), "value");
  settings->bind("clip-level", clip_level->get_adjustment().get(), "value");
  settings->bind("iterations", iterations->get_adjustment().get(), "value");
  settings->bind("adaptive-distortion", adaptive_distortion->get_adjustment().get(), "value");
  settings->bind("output-gain", output_gain->get_adjustment().get(), "value");
  settings->bind("auto-level", auto_level, "active");
  settings->bind("diff-only", diff_only, "active");
  settings->bind("protection125", protection125->get_adjustment().get(), "value");
  settings->bind("protection250", protection250->get_adjustment().get(), "value");
  settings->bind("protection500", protection500->get_adjustment().get(), "value");
  settings->bind("protection1000", protection1000->get_adjustment().get(), "value");
  settings->bind("protection2000", protection2000->get_adjustment().get(), "value");
  settings->bind("protection4000", protection4000->get_adjustment().get(), "value");
  settings->bind("protection8000", protection8000->get_adjustment().get(), "value");
  settings->bind("protection16000", protection16000->get_adjustment().get(), "value");

  prepare_scale(input_gain, "");
  prepare_scale(output_gain, "");

  prepare_spinbutton(clip_level, "dB");
}

PsyClipperUi::~PsyClipperUi() {
  util::debug(name + " ui destroyed");
}

auto PsyClipperUi::add_to_stack(Gtk::Stack* stack, const std::string& schema_path) -> PsyClipperUi* {
  auto builder = Gtk::Builder::create_from_resource("/com/github/wwmm/easyeffects/ui/psyclipper.ui");

  auto* ui = Gtk::Builder::get_widget_derived<PsyClipperUi>(builder, "top_box", "com.github.wwmm.easyeffects.psyclipper",
                                                         schema_path + "psyclipper/");

  auto stack_page = stack->add(*ui, plugin_name::psyclipper);

  return ui;
}

void PsyClipperUi::reset() {
  bypass->set_active(false);

  settings->reset("input-gain");

  settings->reset("output-gain");

  settings->reset("clip-level");

  settings->reset("auto-level");

  settings->reset("diff-only");

  settings->reset("adaptive-distortion");

  settings->reset("iterations");

  settings->reset("protection125");
  settings->reset("protection250");
  settings->reset("protection500");
  settings->reset("protection1000");
  settings->reset("protection2000");
  settings->reset("protection4000");
  settings->reset("protection8000");
  settings->reset("protection16000");
}

void PsyClipperUi::on_new_protection_reduction(double value) {
  protection_reduction->set_value(1.0 - value);

  protection_reduction_label->set_text(level_to_localized_string(util::linear_to_db(value), 0));
}
