Output output/mv.mp4

Set Shell zsh
Set Theme "GitHub Dark"
Set Width 1920
Set Height 1080
Set FontSize 32
Set FontFamily "JetBrainsMonoNF Nerd Font"
Set TypingSpeed 300ms

Hide
Type "touch {A..F}"
Enter 2
Type ": Rename B to myfile"
Enter
Show
Type "mv B myfile"
Enter 2

Hide
Type ": Make a backup of each existing destination file."
Enter
Show
Type "mv --backup A C" # A,B doesn't exist
Enter 2
Sleep 2s

Hide
Type ": Force overwrite file if exists"
Enter
Show
Type "mv -f C D"
Enter 2
Sleep 2s

Hide
Type ": Overwrite file interactively if exists"
Enter
Show
Type "yes | mv -i C D" # A..C doesn't exist
Enter 2
Sleep 2s

Hide
Type ": Verbose output prints each file"
Enter
Show
Type "mv -v C D"
Enter 2
Sleep 2s

