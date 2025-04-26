# File originally generated via Chat GPT Prompt
# Version: 03 (Modified from Chat GPT suggestion)

# python csv_to_folders.py titles.csv
# python csv_to_folders.py -f <file-name.csv> -o <output_dir> -c <column-index> -fnc <Either 'devs' or 'regular'>

import os
import csv
import re
import argparse

# === DEFAULT CONFIGURATIONS ===
default_file_csv = 'titles.csv'     # Path to your CSV file
default_output_directory = 'folders'     # Directory where folders will be created
default_column_index = 0                 # Index of the column with titles (0 for first column)
default_folder_naming_convention = 'regular'

# === ARGUMENT PARSER SETUP ===
parser = argparse.ArgumentParser(description='Create folders from CSV titles.')
parser.add_argument('-f','--file_csv', default=default_file_csv, help='Path to CSV file')
parser.add_argument('-o', '--output', default=default_output_directory, help='Output directory')
parser.add_argument('-c', '--column', type=int, default=default_column_index, help='Column index (default: 0)')
parser.add_argument('-fnc', '--folder_naming_convention', default=default_folder_naming_convention, help='Enable strict folder name sanitization')

args = parser.parse_args()

# String replacements dictionary
replacements = {
	': ': '_',
	'/': '_',
	'&': 'N',
	'+': 'plus',
	'%': 'per',
	'@': 'at',
	'<=': 'LE'
}

def smart_title(text):
	# Split on space, dash, or underscore, but keep the separators!
	parts = re.split(r'([ _-])', text)
	
	result = []
	for part in parts:
		if part in [' ', '_', '-']:
			result.append(part)  # Keep the separator
		elif part.isupper():
			result.append(part)  # Already uppercase, keep it
		elif part.islower():
			result.append(part)  # Already lowercase, keep it
		else:
			result.append(part.capitalize())  # Otherwise capitalize normally
	return ''.join(result)

# === FUNCTION TO SANITIZE FOLDER NAMES ===
def sanitize_folder_name(name, folder_naming_convention):
	
	if folder_naming_convention == 'devs':
		# Enforce smart capital case
		# Edit: commenting out, not necessary?
		#name = smart_title(name)
		# Replace ' - ' with '-'
		name = re.sub(r' - ', '-', name)
		for symbol, replacement in replacements.items():
			name = name.replace(symbol, replacement)
		# Replace comma and spaces (', ') with underscores
		name = re.sub(r', ', '_', name)
		# Replace spaces with dashes
		name = re.sub(r'\s+', '-', name)
		# Keep only safe characters
		name = re.sub(r'[^A-Za-z0-9_\- ]+', '', name)
	# Remove invalid characters
	name = re.sub(r'[\\/*?:"<>|]', '', name)
	# The strip() method removes any leading, and trailing whitespaces.
	name = name.strip()
	return name

# === MAKE OUTPUT DIRECTORY IF NOT EXISTS ===
os.makedirs(args.output, exist_ok=True)

# === READ CSV AND CREATE FOLDERS ===
with open(args.file_csv, 'r', newline='', encoding='utf-8') as file:
	reader = csv.reader(file)
	for row in reader:
		if len(row) > args.column:
			folder_name = sanitize_folder_name(row[args.column], folder_naming_convention = args.folder_naming_convention)
			folder_path = os.path.join(args.output, folder_name)
			try:
				os.makedirs(folder_path, exist_ok=True)
				print(f"Created: {folder_path}")
			except Exception as e:
				print(f"Failed to create {folder_path}: {e}")