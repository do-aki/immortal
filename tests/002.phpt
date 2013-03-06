--TEST--
continue 
--SKIPIF--
<?php if (!extension_loaded("immortal")) print "skip"; ?>
--FILE--
<?php 
ini_set('immortal.throw_exception_at_exit', 1);

function hoge() {
  die("die!");
}

try {
  hoge();
} catch (RuntimeException $e) {
  print "run!";
}

--EXPECT--
run!
