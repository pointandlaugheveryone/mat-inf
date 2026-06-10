import numpy as np
import ctypes
from typing import Optional, Tuple

class StudentBot:
    def __init__(self, name: str = "My Student Bot"):
        self.name = name
        self.l = ctypes.CDLL("./player.so")
        # noinspection PyDeprecation
        self.l.chooseMove.argtypes = [
            np.ctypeslib.ndpointer(dtype=np.int8, flags="C_CONTIGUOUS"),
            ctypes.c_int, ctypes.c_int,
            ctypes.c_int, ctypes.c_int,
            ctypes.POINTER(ctypes.c_int),ctypes.POINTER(ctypes.c_int)
        ]
        self.l.chooseMove.restype = None

    def choose_move(
        self,
        board: np.ndarray,
        player: int,
        win_length: int
    ) -> Optional[Tuple[int, int]]:

        r,c = board.shape
        c_board = np.ascontiguousarray(board).astype(np.int8,copy=False)
        outr = ctypes.c_int(-1)
        outc = ctypes.c_int(-1)
        self.l.ChooseMove(c_board, r,c, player, win_length, ctypes.byref(outr), ctypes.byref(outc))
        return int(outr.value), int(outc.value)