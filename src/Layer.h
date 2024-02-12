#pragma once

namespace my_main{
    // ピクチャの表示レイヤ 後ろにあるほど画面の前面に近い  The display layer of the picture. The further back it is, the closer it is to the front of the screen.
    enum Layer{
        BACK,
        HOR_LINE,
        VER_LINE,
        NUMBER,
        UI
    };
}