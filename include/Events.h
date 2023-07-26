#pragma once

namespace Events {
    class InputEventHandler : public RE::BSTEventSink<RE::InputEvent*> {
    protected:
        InputEventHandler() = default;

    public:
        InputEventHandler(const InputEventHandler&) = delete;
        InputEventHandler(InputEventHandler&&) = delete;
        InputEventHandler& operator=(const InputEventHandler&) = delete;
        InputEventHandler& operator=(InputEventHandler&&) = delete;

        static InputEventHandler* GetSingleton();

        RE::BSEventNotifyControl ProcessEvent(RE::InputEvent* const* a_event, RE::BSTEventSource<RE::InputEvent*>* a_eventSource) override;

        static void Register();
    };
}
