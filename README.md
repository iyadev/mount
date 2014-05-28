A little c++ software for execute script on boot, with vm detection.

Setup : 
  - See your linux wiki for add on boot apps.
  - On Windows add to startup, in start menu.
  - Modify your script path.
  - Modify line 63 the vendor name.

Use : 
  - Add native_start file for execute script on no vm
  - Add native_stop file for execute script on no vm, poweroff
  - Add virtualbox_start file for execute script on vm
  - Add virtualbox_stop file for execute script on vm, poweroff
