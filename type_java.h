/*
 * Copyright (C) 2015, The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef AIDL_TYPE_JAVA_H_
#define AIDL_TYPE_JAVA_H_

#include <string>
#include <vector>

#include "ast_java.h"

namespace android {
namespace aidl {

using std::string;
using std::vector;

class Type {
 public:
  // kinds
  enum { BUILT_IN, USERDATA, INTERFACE, GENERATED };

  // WriteToParcel flags
  enum { PARCELABLE_WRITE_RETURN_VALUE = 0x0001 };

  Type(const string& name, int kind, bool canWriteToParcel, bool canBeOut);
  Type(const string& package, const string& name, int kind,
       bool canWriteToParcel, bool canBeOut, const string& declFile = "",
       int declLine = -1);
  virtual ~Type();

  inline string Package() const { return m_package; }
  inline string Name() const { return m_name; }
  inline string QualifiedName() const { return m_qualifiedName; }
  inline int Kind() const { return m_kind; }
  string HumanReadableKind() const;
  inline string DeclFile() const { return m_declFile; }
  inline int DeclLine() const { return m_declLine; }
  inline bool CanWriteToParcel() const { return m_canWriteToParcel; }
  inline bool CanBeOutParameter() const { return m_canBeOut; }

  virtual string ImportType() const;
  virtual string CreatorName() const;
  virtual string InstantiableName() const;

  virtual void WriteToParcel(StatementBlock* addTo, Variable* v,
                             Variable* parcel, int flags) const;
  virtual void CreateFromParcel(StatementBlock* addTo, Variable* v,
                                Variable* parcel, Variable** cl) const;
  virtual void ReadFromParcel(StatementBlock* addTo, Variable* v,
                              Variable* parcel, Variable** cl) const;

  virtual bool CanBeArray() const;

  virtual void WriteArrayToParcel(StatementBlock* addTo, Variable* v,
                                  Variable* parcel, int flags) const;
  virtual void CreateArrayFromParcel(StatementBlock* addTo, Variable* v,
                                     Variable* parcel, Variable** cl) const;
  virtual void ReadArrayFromParcel(StatementBlock* addTo, Variable* v,
                                   Variable* parcel, Variable** cl) const;

 protected:
  void SetQualifiedName(const string& qualified);
  Expression* BuildWriteToParcelFlags(int flags) const;

 private:
  Type();
  Type(const Type&);

  string m_package;
  string m_name;
  string m_qualifiedName;
  string m_declFile;
  int m_declLine;
  int m_kind;
  bool m_canWriteToParcel;
  bool m_canBeOut;
};

class BasicType : public Type {
 public:
  BasicType(const string& name, const string& marshallParcel,
            const string& unmarshallParcel, const string& writeArrayParcel,
            const string& createArrayParcel, const string& readArrayParcel);

  void WriteToParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                     int flags) const override;
  void CreateFromParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                        Variable** cl) const override;

  bool CanBeArray() const override;

  void WriteArrayToParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                          int flags) const override;
  void CreateArrayFromParcel(StatementBlock* addTo, Variable* v,
                             Variable* parcel, Variable** cl) const override;
  void ReadArrayFromParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                           Variable** cl) const override;

 private:
  string m_marshallParcel;
  string m_unmarshallParcel;
  string m_writeArrayParcel;
  string m_createArrayParcel;
  string m_readArrayParcel;
};

class BooleanType : public Type {
 public:
  BooleanType();

  void WriteToParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                     int flags) const override;
  void CreateFromParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                        Variable** cl) const override;

  bool CanBeArray() const override;

  void WriteArrayToParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                          int flags) const override;
  void CreateArrayFromParcel(StatementBlock* addTo, Variable* v,
                             Variable* parcel, Variable** cl) const override;
  void ReadArrayFromParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                           Variable** cl) const override;
};

class CharType : public Type {
 public:
  CharType();

  void WriteToParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                     int flags) const override;
  void CreateFromParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                        Variable** cl) const override;

  bool CanBeArray() const override;

  void WriteArrayToParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                          int flags) const override;
  void CreateArrayFromParcel(StatementBlock* addTo, Variable* v,
                             Variable* parcel, Variable** cl) const override;
  void ReadArrayFromParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                           Variable** cl) const override;
};

class StringType : public Type {
 public:
  StringType();

  string CreatorName() const override;

  void WriteToParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                     int flags) const override;
  void CreateFromParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                        Variable** cl) const override;

  bool CanBeArray() const override;

  void WriteArrayToParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                          int flags) const override;
  void CreateArrayFromParcel(StatementBlock* addTo, Variable* v,
                             Variable* parcel, Variable** cl) const override;
  void ReadArrayFromParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                           Variable** cl) const override;
};

class CharSequenceType : public Type {
 public:
  CharSequenceType();

  string CreatorName() const override;

  void WriteToParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                     int flags) const override;
  void CreateFromParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                        Variable** cl) const override;
};

class RemoteExceptionType : public Type {
 public:
  RemoteExceptionType();

  void WriteToParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                     int flags) const override;
  void CreateFromParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                        Variable** cl) const override;
};

class RuntimeExceptionType : public Type {
 public:
  RuntimeExceptionType();

  void WriteToParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                     int flags) const override;
  void CreateFromParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                        Variable** cl) const override;
};

class IBinderType : public Type {
 public:
  IBinderType();

  void WriteToParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                     int flags) const override;
  void CreateFromParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                        Variable** cl) const override;

  void WriteArrayToParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                          int flags) const override;
  void CreateArrayFromParcel(StatementBlock* addTo, Variable* v,
                             Variable* parcel, Variable** cl) const override;
  void ReadArrayFromParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                           Variable** cl) const override;
};

class IInterfaceType : public Type {
 public:
  IInterfaceType();

  void WriteToParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                     int flags) const override;
  void CreateFromParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                        Variable** cl) const override;
};

class BinderType : public Type {
 public:
  BinderType();

  void WriteToParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                     int flags) const override;
  void CreateFromParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                        Variable** cl) const override;
};

class BinderProxyType : public Type {
 public:
  BinderProxyType();

  void WriteToParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                     int flags) const override;
  void CreateFromParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                        Variable** cl) const override;
};

class ParcelType : public Type {
 public:
  ParcelType();

  void WriteToParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                     int flags) const override;
  void CreateFromParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                        Variable** cl) const override;
};

class ParcelableInterfaceType : public Type {
 public:
  ParcelableInterfaceType();

  void WriteToParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                     int flags) const override;
  void CreateFromParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                        Variable** cl) const override;
};

class MapType : public Type {
 public:
  MapType();

  void WriteToParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                     int flags) const override;
  void CreateFromParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                        Variable** cl) const override;
  void ReadFromParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                      Variable** cl) const override;
};

class ListType : public Type {
 public:
  ListType();

  string InstantiableName() const override;

  void WriteToParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                     int flags) const override;
  void CreateFromParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                        Variable** cl) const override;
  void ReadFromParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                      Variable** cl) const override;
};

class UserDataType : public Type {
 public:
  UserDataType(const string& package, const string& name, bool builtIn,
               bool canWriteToParcel, const string& declFile = "",
               int declLine = -1);

  string CreatorName() const override;

  void WriteToParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                     int flags) const override;
  void CreateFromParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                        Variable** cl) const override;
  void ReadFromParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                      Variable** cl) const override;

  bool CanBeArray() const override;

  void WriteArrayToParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                          int flags) const override;
  void CreateArrayFromParcel(StatementBlock* addTo, Variable* v,
                             Variable* parcel, Variable** cl) const override;
  void ReadArrayFromParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                           Variable** cl) const override;
};

class InterfaceType : public Type {
 public:
  InterfaceType(const string& package, const string& name, bool builtIn,
                bool oneway, const string& declFile, int declLine);

  bool OneWay() const;

  void WriteToParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                     int flags) const override;
  void CreateFromParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                        Variable** cl) const override;

 private:
  bool m_oneway;
};

class GenericType : public Type {
 public:
  GenericType(const string& package, const string& name,
              const vector<Type*>& args);

  const vector<Type*>& GenericArgumentTypes() const;
  string GenericArguments() const;

  string ImportType() const override;

  void WriteToParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                     int flags) const override;
  void CreateFromParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                        Variable** cl) const override;
  void ReadFromParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                      Variable** cl) const override;

 private:
  string m_genericArguments;
  string m_importName;
  vector<Type*> m_args;
};

class ClassLoaderType : public Type {
 public:
  ClassLoaderType();
};

class GenericListType : public GenericType {
 public:
  GenericListType(const string& package, const string& name,
                  const vector<Type*>& args);

  string CreatorName() const override;
  string InstantiableName() const override;

  void WriteToParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                     int flags) const override;
  void CreateFromParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                        Variable** cl) const override;
  void ReadFromParcel(StatementBlock* addTo, Variable* v, Variable* parcel,
                      Variable** cl) const override;

 private:
  string m_creator;
};

class Namespace {
 public:
  Namespace();
  ~Namespace();
  void Add(Type* type);

  // args is the number of template types (what is this called?)
  void AddGenericType(const string& package, const string& name, int args);

  // lookup a specific class name
  Type* Find(const string& name) const;
  Type* Find(const char* package, const char* name) const;

  // try to search by either a full name or a partial name
  Type* Search(const string& name);

  void Dump() const;

 private:
  struct Generic {
    string package;
    string name;
    string qualified;
    int args;
  };

  const Generic* search_generic(const string& name) const;

  vector<Type*> m_types;
  vector<Generic> m_generics;
};

extern Namespace NAMES;

extern Type* VOID_TYPE;
extern Type* BOOLEAN_TYPE;
extern Type* BYTE_TYPE;
extern Type* CHAR_TYPE;
extern Type* INT_TYPE;
extern Type* LONG_TYPE;
extern Type* FLOAT_TYPE;
extern Type* DOUBLE_TYPE;
extern Type* OBJECT_TYPE;
extern Type* STRING_TYPE;
extern Type* CHAR_SEQUENCE_TYPE;
extern Type* TEXT_UTILS_TYPE;
extern Type* REMOTE_EXCEPTION_TYPE;
extern Type* RUNTIME_EXCEPTION_TYPE;
extern Type* IBINDER_TYPE;
extern Type* IINTERFACE_TYPE;
extern Type* BINDER_NATIVE_TYPE;
extern Type* BINDER_PROXY_TYPE;
extern Type* PARCEL_TYPE;
extern Type* PARCELABLE_INTERFACE_TYPE;

extern Type* CONTEXT_TYPE;

extern Expression* NULL_VALUE;
extern Expression* THIS_VALUE;
extern Expression* SUPER_VALUE;
extern Expression* TRUE_VALUE;
extern Expression* FALSE_VALUE;

void register_base_types();

}  // namespace aidl
}  // namespace android

#endif  // AIDL_TYPE_JAVA_H_
