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

#include "psyclipper_preset.hpp"

PsyClipperPreset::PsyClipperPreset() {
  input_settings = Gio::Settings::create("com.github.wwmm.easyeffects.psyclipper",
                                         "/com/github/wwmm/easyeffects/streaminputs/psyclipper/");

  output_settings = Gio::Settings::create("com.github.wwmm.easyeffects.psyclipper",
                                          "/com/github/wwmm/easyeffects/streamoutputs/psyclipper/");
}

void PsyClipperPreset::save(nlohmann::json& json,
                         const std::string& section,
                         const Glib::RefPtr<Gio::Settings>& settings) {
  json[section]["psyclipper"]["input-gain"] = settings->get_double("input-gain");

  json[section]["psyclipper"]["output-gain"] = settings->get_double("output-gain");

  json[section]["psyclipper"]["clip-level"] = settings->get_double("clip-level");

  json[section]["psyclipper"]["auto-level"] = settings->get_boolean("auto-level");

  json[section]["psyclipper"]["diff-only"] = settings->get_boolean("diff-only");

  json[section]["psyclipper"]["adaptive-distortion"] = settings->get_double("adaptive-distortion");

  json[section]["psyclipper"]["iterations"] = settings->get_int("iterations");

  json[section]["psyclipper"]["protection125"] = settings->get_int("protection125");
  json[section]["psyclipper"]["protection250"] = settings->get_int("protection250");
  json[section]["psyclipper"]["protection500"] = settings->get_int("protection500");
  json[section]["psyclipper"]["protection1000"] = settings->get_int("protection1000");
  json[section]["psyclipper"]["protection2000"] = settings->get_int("protection2000");
  json[section]["psyclipper"]["protection4000"] = settings->get_int("protection4000");
  json[section]["psyclipper"]["protection8000"] = settings->get_int("protection8000");
  json[section]["psyclipper"]["protection16000"] = settings->get_int("protection16000");
}

void PsyClipperPreset::load(const nlohmann::json& json,
                         const std::string& section,
                         const Glib::RefPtr<Gio::Settings>& settings) {
  update_key<double>(json.at(section).at("psyclipper"), settings, "input-gain", "input-gain");

  update_key<double>(json.at(section).at("psyclipper"), settings, "output-gain", "output-gain");

  update_key<double>(json.at(section).at("psyclipper"), settings, "clip-level", "clip-level");

  update_key<bool>(json.at(section).at("psyclipper"), settings, "auto-level", "auto-level");

  update_key<bool>(json.at(section).at("psyclipper"), settings, "diff-only", "diff-only");

  update_key<double>(json.at(section).at("psyclipper"), settings, "adaptive-distortion", "adaptive-distortion");

  update_key<int>(json.at(section).at("psyclipper"), settings, "iterations", "iterations");

  update_key<int>(json.at(section).at("psyclipper"), settings, "protection125", "protection125");
  update_key<int>(json.at(section).at("psyclipper"), settings, "protection250", "protection250");
  update_key<int>(json.at(section).at("psyclipper"), settings, "protection500", "protection500");
  update_key<int>(json.at(section).at("psyclipper"), settings, "protection1000", "protection1000");
  update_key<int>(json.at(section).at("psyclipper"), settings, "protection2000", "protection2000");
  update_key<int>(json.at(section).at("psyclipper"), settings, "protection4000", "protection4000");
  update_key<int>(json.at(section).at("psyclipper"), settings, "protection8000", "protection8000");
  update_key<int>(json.at(section).at("psyclipper"), settings, "protection16000", "protection16000");
}
