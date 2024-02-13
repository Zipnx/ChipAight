#!/usr/bin/python3

'''
This works for now, will polish some other time, although i do say that about everything
'''

import opcodes
import argparse, struct

from os.path import exists as fileExists
from os.path import isdir as isDirectory

def disassemble_file(filepath: str) -> None:

    if not fileExists(filepath) or isDirectory(filepath):
        print('[!] Invalid path')
        return


    with open(filepath, 'rb') as f:
        
        addr = 0x200

        while True:

            data: bytes = f.read(2)

            if len(data) != 2: break

            instruction = struct.unpack('>H', data)[0]

            print(f'0x{addr:03x} |', opcodes.op2string(instruction))

            addr += 2


def main():

    parser = argparse.ArgumentParser(description = 'A disassembler for CHIP-8 bytecode')

    parser.add_argument('infile', type=str, help = 'Bytecode file to disassemble')

    args = parser.parse_args()

    disassemble_file(args.infile)

if __name__ == '__main__': main()
