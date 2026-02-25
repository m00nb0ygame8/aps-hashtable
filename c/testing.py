import hashtable
print("module loaded")

h = hashtable.HashTable()
print("created")

h.add("apple")
h.add("banana")
print("insert ok")

print("apple" in h)
print("banana" in h)
print("pear" in h)

print(len(h))

h.remove("apple")
print("apple" in h)
print(len(h))