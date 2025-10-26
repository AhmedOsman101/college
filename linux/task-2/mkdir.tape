Output output/mkdir.mp4

Set Shell zsh
Set Theme "GitHub Dark"
Set Width 1920
Set Height 1080
Set FontSize 32
Set FontFamily "JetBrainsMonoNF Nerd Font"
Set TypingSpeed 300ms

Type "mkdir ~/Desktop/test"
Enter 2
Sleep 2s

Hide
Type ": By default mkdir would fail if parent does not exist"
Enter
Show
Type "mkdir foo/bar/baz"
Enter 2

Hide
Type ": Use -p to create the parent automatically"
Enter
Show
Type "mkdir -p foo/bar/baz"
Enter 2
Sleep 2s

Hide
Type ": Verbose output"
Enter
Show
Type "mkdir -v test"
Enter 2
Sleep 2s

Hide
Type ": 'Create a directory with given permissions (mode)'"
Enter
Show
Type "mkdir -m 777 public"
Enter 2
Type "mkdir -m 700 private"
Enter 2
Sleep 2s
