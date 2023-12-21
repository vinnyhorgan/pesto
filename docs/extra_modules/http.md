# http

The `http` module allows performing HTTP requests.

First, it needs to be required:

``` lua
local http = require("http")
```

## Functions

### http.request

Performs an HTTP request, blocking until it completes.

```
status, data, headers = http.request(url, [options])
```

**Arguments**

| Name      | Type   | Description                                  |
| --------- | ------ | -------------------------------------------- |
| `url`     | string | The URL to request.                          |
| `options` | table  | Advanced options for the request. (optional) |

`options.method` is the HTTP method to use, also called the verb.
GET is used by default if there's no data in the request, otherwise it defauls to POST. It will be converted to all-caps.

`options.data` is the data to send to the server, also called the body.
It can be a few different types:

- When data is `nil`, no request body will be sent (and method will default to GET).
- When data is a `string`, the string will be used directly as the request body.
- When data is a `table`, then pairs in the table will be URL encoded and concatenated together to form an application/x-www-form-urlencoded body.
For example, if data is { n = 10, k = 'v!' }, then the request body will be something like k=v%21&n=10.
Table pairs will only be used if the key is a string and the value is a string or number.
- When data is a `lightuserdata`, the data pointed to by the lightuserdata will be used as the request body.
Additionally, the datasize option should be an integer indicating how big the request body is, in bytes.
- When `options.data` is set, the Content-Type request header will default to application/x-www-urlencoded unless it's set to something else.

`options.headers` is a table of request headers to send to the server.
Pairs in the table will only be used if the key is a string and the value is a string or number.

**Returns**

| Name      | Type   | Description           |
| --------- | ------ | --------------------- |
| `status`  | number | The HTTP status code. |
| `data`    | string | The response body.    |
| `headers` | table  | The response headers. |

If an error occurs, the function returns `nil, errormessage`.
