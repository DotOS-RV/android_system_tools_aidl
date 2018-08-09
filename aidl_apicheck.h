/*
 * Copyright (C) 2018, The Android Open Source Project *
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
#ifndef AIDL_AIDL_APICHECK_H_
#define AIDL_AIDL_APICHECK_H_

#include "io_delegate.h"
#include "options.h"

namespace android {
namespace aidl {

// Compare the two API dumps, which are given as input files, and test whether
// the second API dump is backwards compatible with the first API dump.
bool check_api(const Options& options, const IoDelegate& io_delegate);

}  // namespace aidl
}  // namespace android

#endif  // AIDL_AIDL_APICHECK_H_
