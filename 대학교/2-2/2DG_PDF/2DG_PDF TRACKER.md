---
cssclasses:
  - cards
  - cards-cover
  - cards-2-3
  - table-max
---

2DG 자료

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
