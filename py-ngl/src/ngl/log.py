import logging
import sys


class ColoredFormatter(logging.Formatter):
    COLORS = {
        logging.DEBUG: "\033[37m",  # White
        logging.INFO: "\033[36m",  # Cyan
        logging.WARNING: "\033[33m",  # Yellow
        logging.ERROR: "\033[31m",  # Red
        logging.CRITICAL: "\033[41m",  # Red background
    }
    RESET = "\033[0m"

    def format(self, record):
        log_message = super().format(record)
        return f"{self.COLORS.get(record.levelno, '')}{log_message}{self.RESET}"


def setup_logger():
    logger = logging.getLogger("ngl")
    if not logger.handlers:
        logger.setLevel(logging.DEBUG)
        file_handler = logging.FileHandler("NGLDebug.log", mode="w")
        console_handler = logging.StreamHandler(sys.stdout)

        file_formatter = logging.Formatter(
            "%(asctime)s - %(levelname)s - %(message)s",
            datefmt="%H:%M:%S",
        )
        console_formatter = ColoredFormatter(
            "%(asctime)s - %(levelname)s - %(message)s",
            datefmt="%H:%M:%S",
        )

        file_handler.setFormatter(file_formatter)
        console_handler.setFormatter(console_formatter)

        logger.addHandler(file_handler)
        logger.addHandler(console_handler)
    return logger


logger = setup_logger()
