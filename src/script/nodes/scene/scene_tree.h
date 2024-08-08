// This file is part of the Godot Orchestrator project.
//
// Copyright (c) 2023-present Crater Crash Studios LLC and its contributors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//		http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#ifndef ORCHESTRATOR_SCRIPT_NODE_SCENE_TREE_H
#define ORCHESTRATOR_SCRIPT_NODE_SCENE_TREE_H

#include "script/script.h"

/// Acquire a reference to the scene tree.
class OScriptNodeSceneTree : public OScriptNode
{
    ORCHESTRATOR_NODE_CLASS(OScriptNodeSceneTree, OScriptNode);
    static void _bind_methods() { }

protected:
    //~ Begin OScriptNode Interface
    void _upgrade(uint32_t p_version, uint32_t p_current_version) override;
    //~ End OScriptNode Interface

public:
    //~ Begin OScriptNode Interface
    void allocate_default_pins() override;
    String get_tooltip_text() const override;
    String get_node_title() const override;
    String get_node_title_color_name() const override { return "scene"; }
    String get_icon() const override;
    String get_help_topic() const override;
    OScriptNodeInstance* instantiate() override;
    //~ End OScriptNode Interface
};

#endif  // ORCHESTRATOR_SCRIPT_NODE_SCENE_TREE_H
