/*
 * Copyright (C) 2020 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <aidl/android/hardware/biometrics/fingerprint/BnCancellationSignal.h>

#include "Session.h"

namespace aidl::android::hardware::biometrics::fingerprint {

class CancellationSignal : public BnCancellationSignal {
  public:
    ndk::ScopedAStatus cancel() override { return ndk::ScopedAStatus::ok(); }
};

Session::Session(std::shared_ptr<ISessionCallback> cb) : cb_(std::move(cb)) {}

ndk::ScopedAStatus Session::enroll(int32_t /*cookie*/, const keymaster::HardwareAuthToken& /*hat*/,
                                   std::shared_ptr<ICancellationSignal>* /*return_val*/) {
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus Session::authenticate(int32_t /*cookie*/, int64_t /*keystoreOperationId*/,
                                         std::shared_ptr<ICancellationSignal>* return_val) {
    if (cb_) {
        cb_->onStateChanged(0, SessionState::AUTHENTICATING);
    }
    *return_val = SharedRefBase::make<CancellationSignal>();
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus Session::detectInteraction(
        int32_t /*cookie*/, std::shared_ptr<ICancellationSignal>* /*return_val*/) {
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus Session::enumerateEnrollments(int32_t /*cookie*/) {
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus Session::removeEnrollments(int32_t /*cookie*/,
                                              const std::vector<int32_t>& /*enrollmentIds*/) {
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus Session::getAuthenticatorId(int32_t /*cookie*/) {
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus Session::resetLockout(int32_t /*cookie*/,
                                         const keymaster::HardwareAuthToken& /*hat*/) {
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus Session::onPointerDown(int32_t /*pointerId*/, int32_t /*x*/, int32_t /*y*/,
                                          float /*minor*/, float /*major*/) {
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus Session::onPointerUp(int32_t /*pointerId*/) {
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus Session::onUiReady() {
    return ndk::ScopedAStatus::ok();
}

}  // namespace aidl::android::hardware::biometrics::fingerprint
