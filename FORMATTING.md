# How `DOCS.md` is formatted: 

##
### Files

Each file has its own section. All functions in a file go under the appropriate section. 

```
# 
### filename.hpp

...

```

##
### Functions

```
##
#### name
`name as appears in code`

Description of the function (what it does, explanation of any parameters.)

[Optional example]
###### Example:

code

output
```

##
#### Classes

```
##
#### name
`name as appears in code`

Description of class (what it does/can be used for.)

#### *constructors:*

##### `constructor as appears in code`

Explanation of constructor. 

...

#### *variables:*

#### variable name
`variable name as appears in code`

Explanation of variable. 

...

#### *methods:*

##### method name
`method name as appears in code`

Description of method. 

...

#### *operators:*

##### operator
`operator as appears in code`

Description of operator. 

...

[Optional example]
###### Example:

code

output
```

##
#### Namespaces

```
##
#### namespace name

Description of namespace. 

`namespace item 1`

Explanation of namespace item 1. 

`namespace item 2`

...

```


##
#### Variables

```
##
#### name
`name as appears in code`

Description of variable
```

If something is OS specific:
```
[name, name in code]
###### *(OS) only*

```

##
#### Comment tags

Mostly just to keep track of things. You would put the tag in a comment next to the code that it applies to. 

`<FIX>` - doesnt work, fix it later

`<BAD>` - quick fix, could work better

`<OSS>` - OS specific, but make cross platform later

`<ODD>` - its odd but just leave it alone

`<UNS>` - unsure if it works fully
