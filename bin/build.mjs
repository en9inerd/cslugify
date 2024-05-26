import { readFile, writeFile } from 'fs/promises';

async function updateCharMap() {
  const data = await readFile('config/charmap.json', 'utf8').catch((err) => {
    console.error('Error reading charmap.json:', err);
    return null;
  });

  if (!data) return;

  try {
    const charMap = JSON.parse(data);

    let cCode = `static const CharMapEntry charMap[MAX_CHAR_MAP] = {\n`;
    for (const [key, value] of Object.entries(charMap)) {
      cCode += `    {L'${(key === '$' ? '$$' : key)}', "${value}"},\n`;
    }
    cCode += `};`;

    const fileData = await readFile('cslugify.c', 'utf8').catch((err) => {
      console.error('Error reading cslugify.c:', err);
      return null;
    });

    if (!fileData) return;

    const updatedFileData = fileData.replace(/static const CharMapEntry charMap\[MAX_CHAR_MAP\] = \{[\s\S]*?\};/, cCode);

    await writeFile('cslugify.c', updatedFileData, 'utf8').catch((err) => {
      console.error('Error writing to cslugify.c:', err);
    });
    console.log('CharMap updated successfully!');
  } catch (error) {
    console.error('Error parsing charmap.json:', error);
  }
}

async function updateLocales() {
  const data = await readFile('config/locales.json', 'utf8').catch((err) => {
    console.error('Error reading locales.json:', err);
    return null;
  });

  if (!data) return;

  try {
    const locales = JSON.parse(data);

    let localesCode = `static const Locale locales[MAX_LOCALES] = {\n`;
    for (const [localeKey, localeData] of Object.entries(locales)) {
      const { locale, ...entries } = localeData;
      localesCode += `    {\n        "${localeKey}",\n        {\n`;
      for (const [key, value] of Object.entries(entries)) {
        localesCode += `            {L'${(key === '$' ? '$$' : key)}', "${value}"},\n`;
      }
      localesCode += `        },\n        ${Object.keys(entries).length}\n    },\n`;
    }
    localesCode += `};`;

    const fileData = await readFile('cslugify.c', 'utf8').catch((err) => {
      console.error('Error reading cslugify.c:', err);
      return null;
    });

    if (!fileData) return;

    const updatedFileData = fileData.replace(/static const Locale locales\[MAX_LOCALES\] = \{[\s\S]*?\};/, localesCode);

    await writeFile('cslugify.c', updatedFileData, 'utf8').catch((err) => {
      console.error('Error writing to cslugify.c:', err);
    });
    console.log('Locales updated successfully!');
  } catch (error) {
    console.error('Error parsing locales.json:', error);
  }
}

async function main() {
  await updateCharMap();
  await updateLocales();
}

main();
