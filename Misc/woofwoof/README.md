# Description
 
Texas A&M's own Miss Reveille has been followed going to the Computing Services 
Complex by paparazi from The Battalion. Since she wants to keep this visit to the CSC private, we have apprehended the cameras from the paparazzi and have begun deleting all the photos. However, during our investigation we came
across one photo that seemed a little suspicious. Can you help us figure out what is happening?

# Documetation

A simple steganography challenge incorporating the analysis of metadata and a simple cipher challenge with the results.

## Setup

1. Deliver the user the image, *reveille.jpg*

# Solution

This challenge should a simple steganography challenge. The encrypted flag can be discovered by looking at the images metadata. The encrypted flag is very blantant as it refers to dog noises and is listed as a comment.



```
exiftool reveille.jpg
```

The flag contains all dog related words, "woof", "bark", and "ruff". The user can, either by hand or by script, translate these words into the components of morse, "-", ".", and " " respectively.


Once the words are translated to morse. The morse can be translated to plain text and the flag is available.
