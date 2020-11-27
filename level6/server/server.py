@app.route('/')
def hello_world():
    return 'Hello World!'

@app.route('/about')
def about():
    str = "<H1>ELEC351</H1>"
    return str

if __name__ == '__main__':
    app.run()