# Create hash table with set()
words = set()

def load(dictionary):
    # Open dictionary as file
    file = open(dictionary, "r")
    # For each line in dictionary file
    for line in file:
        # Set word to line (removing spaces)
        word = line.rstrip()
        # Add word to hash table
        words.add(word)
    # Close file
    file.close
    return True

# Find number of words in hash table
# Done with len() function
def size():
    return len(words)

# Search for word in hash table
# Done with "if word in words"
def check(word):
    if word.lower() in words:
        return true
    else:
        return false

# Done by Python / Not Needed
def unload():
    return True