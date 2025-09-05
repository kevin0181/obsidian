

```dataview
table without id
    "!" + file.link as PDF,
    file.name as Name
from "대학교/3-2/네트워크 게임 프로그래밍/pdf"
where file.ext = "pdf"
sort file.name asc
```

