
def format_hex(data: bytes, group_size: int = 4) -> str:
    hex_str = data.hex()  
    formatted = " ".join(
        hex_str[i:i + group_size * 2] for i in range(0, len(hex_str), group_size * 2)
    )
    return formatted.upper()

