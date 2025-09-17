import logging
import sys


def setup_logger():
    logger = logging.getLogger("ngl")
    if not logger.handlers:
        logger.setLevel(logging.DEBUG)
        file_handler = logging.FileHandler("NGLDebug.log")
        console_handler = logging.StreamHandler(sys.stdout)
        formatter = logging.Formatter(
            "%(asctime)s - %(name)s - %(levelname)s - %(message)s"
        )
        file_handler.setFormatter(formatter)
        console_handler.setFormatter(formatter)
        logger.addHandler(file_handler)
        logger.addHandler(console_handler)
    return logger


logger = setup_logger()
