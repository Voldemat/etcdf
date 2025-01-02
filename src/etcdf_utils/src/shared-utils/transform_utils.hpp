#pragma once
template <class T>
const auto transform_convert = [](const auto &url) { return T(url); };
