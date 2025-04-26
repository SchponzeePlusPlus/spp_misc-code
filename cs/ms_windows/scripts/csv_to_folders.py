# File originally generated via Chat GPT Prompt
# Version: 02 (Chat GPT generated)

import os
import csv
import re
import argparse

# === ARGUMENT PARSER SETUP ===
parser = argparse.ArgumentParser(description='Create folders from CSV titles.')
parser.add_argument('csv', help='Path to CSV file')
parser.add_argument('-o', '--output', default='folders', help='Output directory')
parser.add_argument('-c', '--column', type=int, default=0, help='Column index (default: 0)')
parser.add_argument('--strict', action='store_true', help='Enable strict folder name sanitization')

args = parser.parse_args()

# === FOLDER NAME SANITIZATION ===
def sanitize_folder_name(name, strict=False):
    name = name.strip()
    name = re.sub(r'[\\/*?:"<>|]', '', name)  # Remove invalid characters
    if strict:
        name = re.sub(r'[^A-Za-z0-9_\- ]+', '', name)  # Keep only safe characters
        name = re.sub(r'\s+', '_', name)  # Replace spaces with underscores
    return name

# === CREATE OUTPUT DIRECTORY ===
os.makedirs(args.output, exist_ok=True)

# === READ CSV AND CREATE FOLDERS ===
with open(args.csv, 'r', newline='', encoding='utf-8') as file:
    reader = csv.reader(file)
    for row in reader:
        if len(row) > args.column:
            folder_name = sanitize_folder_name(row[args.column], strict=args.strict)
            folder_path = os.path.join(args.output, folder_name)
            try:
                os.makedirs(folder_path, exist_ok=True)
                print(f"Created: {folder_path}")
            except Exception as e:
                print(f"Failed to create {folder_path}: {e}")