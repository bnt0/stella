# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: command.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf.internal import enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='command.proto',
  package='stellad.proto',
  serialized_pb=_b('\n\rcommand.proto\x12\rstellad.proto\"\xa4\x02\n\x07\x43ontrol\x12\x37\n\x06\x61\x63tion\x18\x01 \x02(\x0e\x32 .stellad.proto.Control.SysAction:\x05OTHER\x12\x34\n\tshortcuts\x18\x02 \x03(\x0b\x32!.stellad.proto.ShortcutDefinition\x12(\n\x08settings\x18\x03 \x03(\x0b\x32\x16.stellad.proto.Setting\x12\x14\n\x06status\x18\x04 \x01(\x08:\x04true\"j\n\tSysAction\x12\t\n\x05OTHER\x10\x00\x12\x0c\n\x08SHUTDOWN\x10\x01\x12\n\n\x06RELOAD\x10\x02\x12\n\n\x06IGNORE\x10\x03\x12\n\n\x06STATUS\x10\x04\x12\x08\n\x04SAVE\x10\x05\x12\x08\n\x04LIST\x10\x06\x12\x0c\n\x08RESPONSE\x10\x07\"\xbc\x01\n\x12ShortcutDefinition\x12\x0b\n\x03key\x18\x01 \x02(\t\x12%\n\x06\x61\x63tion\x18\x02 \x02(\x0e\x32\x15.stellad.proto.Action\x12\r\n\x05value\x18\x03 \x01(\t\x12\x0f\n\x07\x65nabled\x18\x04 \x01(\x08\x12=\n\x04mode\x18\x05 \x01(\x0e\x32&.stellad.proto.ShortcutDefinition.Mode:\x07\x44\x45\x46\x41ULT\"\x13\n\x04Mode\x12\x0b\n\x07\x44\x45\x46\x41ULT\x10\x00\"G\n\x07Setting\x12\x0b\n\x03key\x18\x01 \x02(\t\x12\"\n\x03\x61\x63t\x18\x02 \x02(\x0e\x32\x15.stellad.proto.Action\x12\x0b\n\x03val\x18\x03 \x01(\t*&\n\x06\x41\x63tion\x12\n\n\x06MODIFY\x10\x00\x12\x07\n\x03\x41\x44\x44\x10\x01\x12\x07\n\x03REM\x10\x02')
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

_ACTION = _descriptor.EnumDescriptor(
  name='Action',
  full_name='stellad.proto.Action',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='MODIFY', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ADD', index=1, number=1,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='REM', index=2, number=2,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=591,
  serialized_end=629,
)
_sym_db.RegisterEnumDescriptor(_ACTION)

Action = enum_type_wrapper.EnumTypeWrapper(_ACTION)
MODIFY = 0
ADD = 1
REM = 2


_CONTROL_SYSACTION = _descriptor.EnumDescriptor(
  name='SysAction',
  full_name='stellad.proto.Control.SysAction',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='OTHER', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='SHUTDOWN', index=1, number=1,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='RELOAD', index=2, number=2,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='IGNORE', index=3, number=3,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='STATUS', index=4, number=4,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='SAVE', index=5, number=5,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='LIST', index=6, number=6,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='RESPONSE', index=7, number=7,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=219,
  serialized_end=325,
)
_sym_db.RegisterEnumDescriptor(_CONTROL_SYSACTION)

_SHORTCUTDEFINITION_MODE = _descriptor.EnumDescriptor(
  name='Mode',
  full_name='stellad.proto.ShortcutDefinition.Mode',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='DEFAULT', index=0, number=0,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=497,
  serialized_end=516,
)
_sym_db.RegisterEnumDescriptor(_SHORTCUTDEFINITION_MODE)


_CONTROL = _descriptor.Descriptor(
  name='Control',
  full_name='stellad.proto.Control',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='action', full_name='stellad.proto.Control.action', index=0,
      number=1, type=14, cpp_type=8, label=2,
      has_default_value=True, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='shortcuts', full_name='stellad.proto.Control.shortcuts', index=1,
      number=2, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='settings', full_name='stellad.proto.Control.settings', index=2,
      number=3, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='status', full_name='stellad.proto.Control.status', index=3,
      number=4, type=8, cpp_type=7, label=1,
      has_default_value=True, default_value=True,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _CONTROL_SYSACTION,
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=33,
  serialized_end=325,
)


_SHORTCUTDEFINITION = _descriptor.Descriptor(
  name='ShortcutDefinition',
  full_name='stellad.proto.ShortcutDefinition',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='key', full_name='stellad.proto.ShortcutDefinition.key', index=0,
      number=1, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='action', full_name='stellad.proto.ShortcutDefinition.action', index=1,
      number=2, type=14, cpp_type=8, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='value', full_name='stellad.proto.ShortcutDefinition.value', index=2,
      number=3, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='enabled', full_name='stellad.proto.ShortcutDefinition.enabled', index=3,
      number=4, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='mode', full_name='stellad.proto.ShortcutDefinition.mode', index=4,
      number=5, type=14, cpp_type=8, label=1,
      has_default_value=True, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _SHORTCUTDEFINITION_MODE,
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=328,
  serialized_end=516,
)


_SETTING = _descriptor.Descriptor(
  name='Setting',
  full_name='stellad.proto.Setting',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='key', full_name='stellad.proto.Setting.key', index=0,
      number=1, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='act', full_name='stellad.proto.Setting.act', index=1,
      number=2, type=14, cpp_type=8, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='val', full_name='stellad.proto.Setting.val', index=2,
      number=3, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=518,
  serialized_end=589,
)

_CONTROL.fields_by_name['action'].enum_type = _CONTROL_SYSACTION
_CONTROL.fields_by_name['shortcuts'].message_type = _SHORTCUTDEFINITION
_CONTROL.fields_by_name['settings'].message_type = _SETTING
_CONTROL_SYSACTION.containing_type = _CONTROL
_SHORTCUTDEFINITION.fields_by_name['action'].enum_type = _ACTION
_SHORTCUTDEFINITION.fields_by_name['mode'].enum_type = _SHORTCUTDEFINITION_MODE
_SHORTCUTDEFINITION_MODE.containing_type = _SHORTCUTDEFINITION
_SETTING.fields_by_name['act'].enum_type = _ACTION
DESCRIPTOR.message_types_by_name['Control'] = _CONTROL
DESCRIPTOR.message_types_by_name['ShortcutDefinition'] = _SHORTCUTDEFINITION
DESCRIPTOR.message_types_by_name['Setting'] = _SETTING
DESCRIPTOR.enum_types_by_name['Action'] = _ACTION

Control = _reflection.GeneratedProtocolMessageType('Control', (_message.Message,), dict(
  DESCRIPTOR = _CONTROL,
  __module__ = 'command_pb2'
  # @@protoc_insertion_point(class_scope:stellad.proto.Control)
  ))
_sym_db.RegisterMessage(Control)

ShortcutDefinition = _reflection.GeneratedProtocolMessageType('ShortcutDefinition', (_message.Message,), dict(
  DESCRIPTOR = _SHORTCUTDEFINITION,
  __module__ = 'command_pb2'
  # @@protoc_insertion_point(class_scope:stellad.proto.ShortcutDefinition)
  ))
_sym_db.RegisterMessage(ShortcutDefinition)

Setting = _reflection.GeneratedProtocolMessageType('Setting', (_message.Message,), dict(
  DESCRIPTOR = _SETTING,
  __module__ = 'command_pb2'
  # @@protoc_insertion_point(class_scope:stellad.proto.Setting)
  ))
_sym_db.RegisterMessage(Setting)


# @@protoc_insertion_point(module_scope)
