# Attribute Parser of Hackerrank

This code is created from Attribute Parser challenge of Hackerrank platform. It takes a list of html-like xml markup expressions and parses all. Then it can be accessed by "." for tags and "\~" for attributes of tags (i.e. tag1\~value, tag1.tag2\~name).

Example inputs:
```
4 3
<tag1 value = "HelloWorld">
<tag2 name = "Name1">
</tag2>
</tag1>
tag1.tag2~name
tag1~name
tag1~value

2 1
<tag1 value = "HelloWorld">
</tag1>
tag1~value

10 10
<a value = "GoodVal">
<b value = "BadVal" size = "10">
</b>
<c height = "auto">
<d size = "3">
<e strength = "2">
</e>
</d>
</c>
</a>
a~value
b~value
a.b~size
a.b~value
a.b.c~height
a.c~height
a.d.e~strength
a.c.d.e~strength
d~sze
a.c.d~size
```
