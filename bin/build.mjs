import { readFile, writeFile } from 'fs/promises';

const data = await readFile('config/charmap.json', 'utf8').catch((err) => {
  console.error('Error reading charmap.json:', err);
  return;
});

try {
  const charMap = JSON.parse(data);

  let cCode = `static const CharMapEntry charMap[MAX_CHAR_MAP] = {\n`;
  for (const [key, value] of Object.entries(charMap)) {
    cCode += `    {L'${(key === '$' ? '$$' : key)}', "${value}"},\n`;
  }
  cCode += `};`;

  const fileData = await readFile('cslugify.c', 'utf8').catch((err) => {
    console.error('Error reading cslugify.c:', err);
    return;
  });

  const updatedFileData = fileData.replace(/static const CharMapEntry charMap\[MAX_CHAR_MAP\] = \{[\s\S]*?\};/, cCode);

  await writeFile('cslugify.c', updatedFileData, 'utf8').catch((err) => {
    console.error('Error writing to cslugify.c:', err);
    return;
  });
  console.log('cslugify.c updated successfully!');
} catch (error) {
  console.error('Error parsing charmap.json:', error);
}
