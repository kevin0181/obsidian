

```dataview
table without id
	"![[ " + file.link + " ]] " as PDF
from #2DG
where file.ext = "pdf"
sort file.name asc
```

