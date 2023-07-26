#include "Events.h"

#include "Utility.h"

namespace Events {
    InputEventHandler* InputEventHandler::GetSingleton() {
        static InputEventHandler singleton;
        return std::addressof(singleton);
    }

    RE::BSEventNotifyControl InputEventHandler::ProcessEvent(RE::InputEvent* const* a_event, RE::BSTEventSource<RE::InputEvent*>* a_eventSource) {
        if (!a_event) return RE::BSEventNotifyControl::kContinue;

        if (!*a_event) return RE::BSEventNotifyControl::kContinue;

        if (const auto ui = RE::UI::GetSingleton()) {
            if (ui->IsItemMenuOpen()) {
                for (auto e = *a_event; e != nullptr; e = e->next) {
                    if (const auto button = e->AsButtonEvent()) {
                        const auto id = button->GetIDCode();
                        const auto device = button->GetDevice();
                        if (device == RE::INPUT_DEVICE::kKeyboard) {
                            if (id == 42 && button->IsHeld()) Utility::shift_held = true;
                            if (id == 42 && button->IsUp() && Utility::shift_held) Utility::shift_held = false;
                        }
                        if (device == RE::INPUT_DEVICE::kMouse) {
                            const auto scancode = SKSE::InputMap::kMacro_MouseButtonOffset + id;
                            const auto manager = RE::Inventory3DManager::GetSingleton();
                            const auto name = manager->tempRef->GetName();
                            if (scancode == 264 && Utility::shift_held) {
                                manager->itemScale += 0.25f;
                                logger::info("Zoom in item {}", name);
                            }
                            if (scancode == 265 && Utility::shift_held) {
                                manager->itemScale -= 0.25f;
                                logger::info("Zoom out item {}", name);
                            }
                        }
                    }
                }
            }
        }

        return RE::BSEventNotifyControl::kContinue;
    }

    void InputEventHandler::Register() {
        const auto manager = RE::BSInputDeviceManager::GetSingleton();
        manager->AddEventSink(GetSingleton());
        logger::info("Registered input event handler");
    }
}
