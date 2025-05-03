#ifndef SCENE_H

struct Scene {
  virtual void log_scene() = 0;
  virtual void next_scene() = 0;

private:
};

#endif // !SCENE_H
