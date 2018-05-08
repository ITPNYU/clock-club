# Clock Animation Test  

This sketch is a quick way to test different clock designs as animations before building them physically. It was inspired by [Mr. Jones Watches](https://mrjoneswatches.com/), which makes many watches with a clear full circle layer as a minute or hour hand, such as the [Time Traveler](https://mrjoneswatches.com/collections/all-watches/products/time-traveller) watch.

To launch the sketch:

``$ python -m SimpleHTTPServer 8080``

then open a browser to ``http://localhost:8080/``

There's a folder called ``assets`` in the sketch that holds three images: ``hourLayer.png``, ``minuteLayer.png``, and ``secondLayer.png``. Put any images you want in there, and they will be placed by the sketch, with the hour on the bottom, minute in the middle, and second on the top. They'll then be rotated like a clock.

For best results, make them all square and all the same size. Make some layers transparent in each image, with most of the secondLayer image being transparent. The images in the folder give you the idea. Note how the second layer's only image is off center. It will rotate at the edge of the clock.

You can change the speed of the clock by changing the ``speed`` variable in ``sketch.js``. By default it runs at 30x normal clock speed. You can also change the transparency of the layers using the ``hAlpha``, ``mAlpha``, and ``sAlpha`` variables. They range from 0 (transparent) to 255 (opaque).
