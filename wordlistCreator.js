const getWordlist = () => {
	const createVariations = x => ([
		x,
		x.replace(/\s/g, ''),
		x[0].toLowerCase() + x.substr(1).replace(/\s/g, ''),
		...(x.split(' '))
	]);

	return [...(document.querySelector('table.sortable').rows)]
			.map(x => x.cells[0].innerText)
			.reduce((all, x) => {
				all.push(...createVariations(x));
				return all;
			}, [])
			.join('\n');
};

const showWordlist = () => {
	const words = getWordlist();
	const textarea = document.createElement('textarea');
	textarea.value = words;
	
	document.body.appendChild(textarea);
}

showWordlist();