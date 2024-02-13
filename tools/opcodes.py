
import struct

INVALID_MSG = 'Invalid op: {0}'

# This can def be cleaned up a bit
def op2string(op: int) -> str:

    optype = (op & 0xf000) >> 12
    regx   = (op & 0x0f00) >> 8
    regy   = (op & 0x00f0) >> 4

    if optype == 0:
        
        if (op & 0xff) == 0xE0:
            return 'CLS'

        elif (op & 0xff) == 0xee:
            return 'RET'

        else:
            return INVALID_MSG.format(hex(op))

    elif optype == 1:

        return f'JP 0x{op & 0xfff:04x}'

    elif optype == 2:

        return f'CALL 0x{op & 0xfff:04x}'

    elif optype == 3:

        return f'SE V{regx:x}, 0x{op & 0xff:02x}'

    elif optype == 4:

        return f'SNE V{regx:x}, 0x{op & 0xff:02x}'

    elif optype == 5:
        
        return f'SE V{regx:x}, V{regy:x}'

    elif optype == 6:

        return f'LD V{regx:x}, 0x{op & 0xff:02x}'

    elif optype == 7:

        return f'ADD V{regx:x}, 0x{op & 0xff:02x}'

    elif optype == 8:

        subtype = op & 0xf

        if subtype == 0:

            return f'LD V{regx:x}, V{regy:x}'

        elif subtype == 1:

            return f'OR V{regx:x}, V{regy:x}'

        elif subtype == 2:

            return f'AND V{regx:x}, V{regy:x}'

        elif subtype == 3:

            return f'XOR V{regx:x}, V{regy:x}'

        elif subtype == 4:

            return f'ADD V{regx:x}, V{regy:x}'

        elif subtype == 5:

            return f'SUB V{regx:x}, V{regy:x}'

        elif subtype == 6:

            return f'SHR V{regx:x}'

        elif subtype == 7:

            return f'SUBN V{regx:x}, V{regy:x}'

        elif subtype == 0xe:

            return f'SHL V{regx:x}'

        else:

            return INVALID_MSG.format(hex(op))
    
    elif optype == 9:

        return f'SNE V{regx:x}, V{regy:x}'

    elif optype == 0xA:

        return f'LD I, 0x{op & 0xfff:03x}'

    elif optype == 0xB:

        return f'JP V0, 0x{op & 0xfff:03x}'

    elif optype == 0xC:

        return f'RND V{regx:x}, 0x{op & 0xff:02x}'

    elif optype == 0xD:

        return f'DRW V{regx:x}, V{regy:x}, 0x{op & 0xf}'
    
    elif optype == 0xE:

        if op & 0xff == 0x9E:
            
            return f'SKP V{regx:x}'

        elif op & 0xff == 0xA1:

            return f'SKNP V{regx:x}'

        else:

            return INVALID_MSG.format(hex(op))
    
    elif optype == 0xF:

        subtype = op & 0xff

        if subtype == 0x07:

            return f'LD V{regx:x}, DT'

        elif subtype == 0x0A:

            return f'LD V{regx:x}, K'

        elif subtype == 0x15:

            return f'LD DT, V{regx:x}'

        elif subtype == 0x18:

            return f'LD ST, V{regx:x}'

        elif subtype == 0x1E:

            return f'ADD I, V{regx:x}'

        elif subtype == 0x29:

            return f'LD F, V{regx:x}'

        elif subtype == 0x33:

            return f'LD B, V{regx:x}'

        elif subtype == 0x55:

            return f'LD [I], V{regx:x}'

        elif subtype == 0x65:

            return f'LD V{regx:x}, [I]'

    
    return INVALID_MSG.format(hex(op))
    


