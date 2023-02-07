<?php
/**
 * Page callback to display the Albums
 **/
function albums_page() {

    // Data request
    $request = drupal_http_request("https://jsonplaceholder.typicode.com/photos");

    $datas = json_decode($request->data, true);
    
    $out = [];
    foreach ($datas as $data) {
        $out[$data['albumId']][] = [
            'id' => $data['id'],
            'title' => $data['title'],
            'url' => $data['url'],
            'thumbnailUrl' => $data['thumbnailUrl'],
        ];
    }

    // Return datas as array in needed structured
    $albums_arr = drupal_json_decode(json_encode($out, JSON_PRETTY_PRINT));

    $albums_html = array();
    foreach ($albums_arr as $key => $item) {
        $thumb = $albums_arr[$key][0]['thumbnailUrl'];    
        $albums_html[] = array(
            '#prefix' => '<div style="margin:3px;width:150px;height:150px;float:left;">',
            '#markup' => l('<img src="' . $thumb . '" alt=""><div style="margin:-30px 0 0 10px;">Album ' . $key . '</div>', 'albums/' . $key, array('html' => TRUE)),
            '#suffix' => '</div>',
        ); 
    }
    
    return $albums_html; 
}

/**
 * Page callback to display list of the Album photos
 **/
function album_photos_page($albid) {

    // Data request
    $request = drupal_http_request("https://jsonplaceholder.typicode.com/photos?albumId=" . $albid);

    // Return datas as array
    $datas = drupal_json_decode($request->data);
/*
    echo "<pre>";
    print_r($datas);
    echo "</pre>";
*/
    $photos_list = array();
    foreach ($datas as $key => $item) {
        $thumb = $datas[$key]['thumbnailUrl']; 
        $photos_list[] = array(
            '#prefix' => '<div style="margin:3px;">',
            '#markup' => '<img src="' . $thumb . '" alt="" style="margin-right:5px;"><strong>' . $datas[$key]['title'] . '</strong>',
            '#suffix' => '</div>',
        );
    }

    return $photos_list;
}