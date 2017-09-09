module.exports = function inspectInstance (instance) {
  var object = instance.constructor.prototype;
  return Object.
          getOwnPropertyNames(object).
          filter( p => Object.getOwnPropertyDescriptor(object, p).get ).
          reduce(
            (m, p) => {
              m[p] = instance[p];
              return m
            },
            {}
          );
}