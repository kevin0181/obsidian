

```dataview
table without id 
	embed(link(img, "300")),
	file.link as Title,
	string(year) as Year, 
	" - " + user as User,
	Number + "번"
from #2DG
where img != null
sort number(Number) desc
```