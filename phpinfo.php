<?php
if( $_SERVER['REMOTE_ADDR'] == '127.0.0.1' || $_SERVER['REMOTE_ADDR'] == '::1')
{
    ob_start();
    phpinfo();
    $pinfo = ob_get_contents();
    ob_end_clean();
    echo str_replace( '<head>', '<head><link rel="shortcut icon" href="/misc/favicon.ico" type="image/x-icon" />', $pinfo);
}
?>