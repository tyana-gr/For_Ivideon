#ifndef LAMPFACE_H
#define LAMPFACE_H

#include <QtGlobal>

namespace protocol {

struct Command {
    quint8 type;
    quint16 length;
};

struct Color {
    quint8 r;
    quint8 g;
    quint8 b;
};

enum Type {
    ON = 0x12,
    OFF = 0x13,
    COLOR = 0x20
};

}

#endif // LAMPFACE_H
