--TEST--
continue 
--SKIPIF--
<?php print "skip"; ?>
--FILE--
<?php 
ini_set('immortal.throw_exception_at_exit', 1);

try {
  die("die!");
} catch (RuntimeException $e) {
  print "run!";
}

--EXPECT--
run!

