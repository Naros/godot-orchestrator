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
#ifndef ORCHESTRATOR_NODE_SET_PROPERTY_H
#define ORCHESTRATOR_NODE_SET_PROPERTY_H

#include "property.h"

/// A script node that supports getting properties on a target
class OScriptNodePropertySet : public OScriptNodeProperty
{
    ORCHESTRATOR_NODE_CLASS(OScriptNodePropertySet, OScriptNodeProperty);
    static void _bind_methods() { }

public:
    //~ Begin OScriptNode Interface
    void allocate_default_pins() override;
    String get_tooltip_text() const override;
    String get_node_title() const override;
    OScriptNodeInstance* instantiate() override;
    //~ End OScriptNode Interface

    void set_default_value(const Variant& p_default_value);
};

#endif  // ORCHESTRATOR_NODE_SET_PROPERTY_H