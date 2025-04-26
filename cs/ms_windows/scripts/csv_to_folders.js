// File originally generated via Chat GPT Prompt
// Version: Original

const fs = require('fs');
const path = require('path');
const readline = require('readline');
const csv = require('csv-parser');

// === CONFIGURATION ===
const csvFilePath = 'titles.csv';         // Path to your CSV file
const outputDirectory = 'folders';        // Where to create folders
const columnName = 'Title';               // Header name of the column (first row in CSV)

// === MAKE OUTPUT DIRECTORY IF NOT EXISTS ===
if (!fs.existsSync(outputDirectory)) {
  fs.mkdirSync(outputDirectory);
}

// === FUNCTION TO SANITIZE FOLDER NAMES ===
function sanitizeFolderName(name) {
  return name.replace(/[\\/:*?"<>|]/g, '').trim();
}

// === READ CSV AND CREATE FOLDERS ===
fs.createReadStream(csvFilePath)
  .pipe(csv())
  .on('data', (row) => {
    const rawTitle = row[columnName];
    if (rawTitle) {
      const folderName = sanitizeFolderName(rawTitle);
      const folderPath = path.join(outputDirectory, folderName);
      if (!fs.existsSync(folderPath)) {
        fs.mkdirSync(folderPath, { recursive: true });
        console.log(`Created: ${folderPath}`);
      }
    }
  })
  .on('end', () => {
    console.log('Folder creation complete.');
  });