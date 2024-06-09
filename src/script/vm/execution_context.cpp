// This file is part of the Godot Orchestrator project.
//
// Copyright (c) 2023-present Vahera Studios LLC and its contributors.
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
#include "script/vm/execution_context.h"

#include "script/instances/node_instance.h"
#include "script/node.h"
#include "script/vm/script_vm.h"

#include <cassert>

int OScriptExecutionStackInfo::get_stack_size() const
{
    int stack_size = 0;
    stack_size += max_stack_size * sizeof(Variant);
    stack_size += node_count * sizeof(bool);
    stack_size += (max_inputs + max_outputs) * sizeof(Variant*);
    stack_size += flow_size * sizeof(int);
    stack_size += pass_size * sizeof(int);

    return stack_size;
}

void OScriptExecutionContext::_initialize_variant_stack()
{
    for (int i = 0; i < _info.max_stack_size; i++)
        memnew_placement(&_variant_stack[i], Variant);
}

void OScriptExecutionContext::_cleanup()
{
    _cleanup_stack(_info, _variant_stack);
}

void OScriptExecutionContext::_cleanup_stack(OScriptExecutionStackInfo& p_info, const Variant* p_stack)
{
    for (int i = 0; i < p_info.max_stack_size; i++)
        p_stack[i].~Variant();
}

Object* OScriptExecutionContext::get_owner()
{
    return _instance->get_owner();
}

void OScriptExecutionContext::set_error(GDExtensionCallErrorType p_type, const String& p_reason)
{
    if (_error)
    {
        _error->error = p_type;
        _error_reason = p_reason;
    }
}

void OScriptExecutionContext::set_invalid_argument(OScriptNodeInstance* p_instance, int p_index, Variant::Type p_type, Variant::Type p_expected_type)
{
    if (_error)
    {
        _error->error = GDEXTENSION_CALL_ERROR_INVALID_ARGUMENT;
        _error->argument = p_index;
        _error->expected = p_expected_type;
        _error_reason = vformat("%s: %d type %s", p_instance->get_base_node()->get_class(), p_instance->get_id(), Variant::get_type_name(p_type));
    }
}

void OScriptExecutionContext::clear_error()
{
    if (_error && _error->error != GDEXTENSION_CALL_OK)
    {
        _error->error = GDEXTENSION_CALL_OK;
        _error_reason = "";
    }
}

void OScriptExecutionContext::copy_inputs_to_outputs(int p_count)
{
    for (int i = 0; i < p_count; i++)
        _outputs[i] = _inputs[i];
}

void OScriptExecutionContext::copy_input_to_output(size_t p_input_index, size_t p_output_index)
{
    *_outputs[p_output_index] = *_inputs[p_input_index];
}

OScriptExecutionContext::OScriptExecutionContext(OScriptExecutionStackInfo p_stack_info, void* p_stack, int p_flow_position, int p_passes)
    : _info(p_stack_info)
    , _stack(p_stack)
{
    assert(_stack != nullptr);

    _variant_stack = static_cast<Variant*>(_stack);
    _execution_stack = reinterpret_cast<bool*>(_variant_stack + _info.max_stack_size);
    _inputs = reinterpret_cast<Variant**>(_execution_stack + _info.node_count);
    _outputs = reinterpret_cast<Variant**>(_inputs + _info.max_inputs);

    const int max_flow = _info.flow_size;
    _flow_stack = max_flow ? reinterpret_cast<int*>(_outputs + _info.max_outputs) : nullptr;
    _pass_stack = _flow_stack ? reinterpret_cast<int*>(_flow_stack + max_flow) : nullptr;

    _flow_stack_position = p_flow_position;
    _passes = p_passes;
}

