#pragma once
namespace MoChengEngine::FrameWork::Wrapper {
template <typename T> class ComponentBase {

  [[nodiscard]] virtual T Get_handle() const= 0;
};

} // namespace MoChengEngine::FrameWork::Wrapper