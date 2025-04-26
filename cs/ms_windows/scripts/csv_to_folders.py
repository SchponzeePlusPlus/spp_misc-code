# File originally generated via Chat GPT Prompt
# Version: Original

import os
import csv
import re

# === CONFIGURATION ===
csv_file_path = 'titles.csv'     # Path to your CSV file
output_directory = 'folders'     # Directory where folders will be created
column_index = 0                 # Index of the column with titles (0 for first column)

# === MAKE OUTPUT DIRECTORY IF NOT EXISTS ===
os.makedirs(output_directory, exist_ok=True)

# === FUNCTION TO SANITIZE FOLDER NAMES ===
def sanitize_folder_name(name):
    # Remove invalid characters and strip whitespace
    name = re.sub(r'[\\/*?:"<>|]', "", name)
    return name.strip()

# === READ CSV AND CREATE FOLDERS ===
with open(csv_file_path, 'r', newline='', encoding='utf-8') as file:
    reader = csv.reader(file)
    for row in reader:
        if len(row) > column_index:
            folder_name = sanitize_folder_name(row[column_index])
            folder_path = os.path.join(output_directory, folder_name)
            try:
                os.makedirs(folder_path, exist_ok=True)
                print(f"Created: {folder_path}")
            except Exception as e:
                print(f"Failed to create {folder_path}: {e}")